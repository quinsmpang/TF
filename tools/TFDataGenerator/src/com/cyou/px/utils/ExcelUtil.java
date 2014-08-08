package com.cyou.px.utils;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.xssf.usermodel.XSSFCell;
import org.apache.poi.xssf.usermodel.XSSFRichTextString;
import org.apache.poi.xssf.usermodel.XSSFRow;
import org.apache.poi.xssf.usermodel.XSSFSheet;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;


/**
 * excel工具类 
 * @author yuebinbin
 * @date 2013-3-26
 */
public class ExcelUtil {
	
	/**
	 * 获取一个sheet
	 * @param filePath
	 * @param sheetIndex
	 * @return
	 * @throws IOException
	 */
	public static XSSFSheet getXSSFSheet(String filePath, int sheetIndex) throws IOException {
		// 检查文件的存在性
		File testExistent = new File(filePath);
		if (!testExistent.exists()) {
			System.out.println("文件不存在：" + filePath);
			return null;
		}
		
		InputStream stream = new FileInputStream(filePath);
		XSSFWorkbook workBook = new XSSFWorkbook(stream);
		XSSFSheet sheet = workBook.getSheetAt(sheetIndex);
		return sheet;
	}
	
	public static boolean getBoolean(XSSFCell cell) {
		if (cell == null)
			return false;
		
		return cell.getBooleanCellValue();
	}
	
	public static String getString(XSSFCell cell) {
		if (cell == null)
			return null;
		
		if (cell.getCellType() == XSSFCell.CELL_TYPE_STRING) {
			XSSFRichTextString text = cell.getRichStringCellValue();
			if (text == null) {
				return null;
			} else {
				return text.getString();
			}
		} else if (cell.getCellType() == XSSFCell.CELL_TYPE_NUMERIC) {
			return String.valueOf(cell.getNumericCellValue());
		} else {
			return null;
		}
	}
	
	public static double getDouble(XSSFCell cell) {
		if (cell == null)
			return 0;
		
		if (cell.getCellType() == XSSFCell.CELL_TYPE_STRING) {
			return Double.valueOf(cell.getStringCellValue());
		} else if (cell.getCellType() == XSSFCell.CELL_TYPE_NUMERIC) {
			return cell.getNumericCellValue();
		} else {
			return 0;
		}
	}

	
	/**
	 * 将excel转换成Array (优化后的方法，对excel的不规则配置容错性提高)
	 * @param filePath
	 * @return Array 下标内容：
	 * 					0：表名
	 * 					1：字段属性类型
	 * 					2：列名称
	 * 					3：标题名称
	 */
	public static String[][] convertExcel2Array(File file) {
		XSSFSheet sheet = null;
		try {
			sheet = ExcelUtil.getXSSFSheet(file.getPath(), 0);
		} catch (IOException e) {
			e.printStackTrace();
		}
		//总体集合
		String[][] excelArr = new String[sheet.getLastRowNum() + 1][];	//标题名称数组
		
		//获取列名称行
		XSSFRow nameRow = sheet.getRow(0);
		String[] nameArr = new String[nameRow.getLastCellNum()];
		for(int i = 0; i < nameRow.getLastCellNum(); i++) {
			Cell cell = nameRow.getCell(i);
			if (cell == null) continue;
			cell.setCellType(Cell.CELL_TYPE_STRING);
			if (!"".equals(cell.toString().trim()))
			{
				nameArr[i] = cell.toString().trim();
			}
		}
		excelArr[0] = nameArr;
		
		//获取列属性行
		XSSFRow proRow = sheet.getRow(1);
		String[] proArr = new String[proRow.getLastCellNum() ];
		for(int i = 0; i < proRow.getLastCellNum(); i++) {
			Cell cell = proRow.getCell(i);
			if (cell == null) continue;
			cell.setCellType(Cell.CELL_TYPE_STRING);
			if (!"".equals(cell.toString().trim()))
			{
				proArr[i] = cell.toString().trim();
			}
		}
		excelArr[1] = proArr;
		
		//获取标题行
		XSSFRow titleRow = sheet.getRow(2);
		String[] titleArr = new String[titleRow.getLastCellNum()]; //标题名称数组
		for (int i = 0; i < titleRow.getLastCellNum(); i++) {
			Cell cell = titleRow.getCell(i);
			if (cell == null) continue;
			cell.setCellType(Cell.CELL_TYPE_STRING);
			if (!"".equals(cell.toString().trim()))
			{
				titleArr[i] = cell.toString().trim();
			}
		}
		excelArr[2] = titleArr;
		
		//获取KEY行
		XSSFRow keyRow = sheet.getRow(3);
		String[] keyArr = new String[keyRow.getLastCellNum()]; //标题名称数组
		for (int i = 0; i < keyRow.getLastCellNum(); i++) {
			Cell cell = keyRow.getCell(i);
			if (cell == null) continue;
			cell.setCellType(Cell.CELL_TYPE_STRING);
			if (!"".equals(cell.toString().trim()))
			{
				keyArr[i] = cell.toString().trim();
			}
		}
		excelArr[3] = keyArr;
		
		//开始正文内容
		int rowNum = sheet.getLastRowNum();
		for (int i = 4; i <= rowNum; i++)
		{
			XSSFRow row = sheet.getRow(i);
			// 一直查到空行
			if (row == null) {
				continue;
			}
			String[] cellArr = new String[nameArr.length];
			for(int j = 0; j < row.getLastCellNum(); j++) {
				if (j >= cellArr.length)
					break;
				Cell cell = row.getCell(j);
				if (cell == null) continue;
				cell.setCellType(Cell.CELL_TYPE_STRING);
				if (!"".equals(cell.toString().trim()))
				{
					cellArr[j] = cell.toString().trim();
				}
			}
			excelArr[i] = cellArr;
		}
		return excelArr;
	}
	
	
	/**
	 * 获得属性类
	 * @param pro
	 * @param name
	 * @return
	 */
	public static List<String> getProList(List<String> pro, List<String> name) {
		List<String> list = new ArrayList<String>();
		StringBuffer s;
		for (int i = 0; i < name.size(); i++)
		{
			s = new StringBuffer();
			s.append(name.get(i)).append("(").append(getType(pro.get(i)));
			list.add(String.valueOf(s));
		}
		return list;
	}

	
	/**
	 * 根据字符串获得类型
	 * @param str
	 * @return
	 */
	public static String getType(String str) {
		if (str == null)
		{
			return "std::string";
		}
		str = str.toLowerCase();
		if ("string".equals(str))
		{
			return "std::string";
		} else if ("int".equals(str)) {
			return "int";
		} else if ("float".equals(str)) {
			return "float";
		} 
		return "undefindType";
	}
	
	public static float getFloat(XSSFCell cell) {
		return (float) getDouble(cell);
	}
	
	public static long getLong(XSSFCell cell) {
		return (long) getDouble(cell);
	}

	public static int getInt(XSSFCell cell) {
		return (int) getDouble(cell);
	}

	public static short getShort(XSSFCell cell) {
		return (short) getDouble(cell);
	}

	public static byte getByte(XSSFCell cell) {
		return (byte) getDouble(cell);
	}
}
