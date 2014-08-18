package com.cyou.px.generator;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.cyou.px.ConfigManager;
import com.cyou.px.PXDataGenerator;
import com.cyou.px.utils.ExcelUtil;
import com.cyou.px.utils.FileUtil;
import com.cyou.px.vo.AttributeVO;

import freemarker.template.Configuration;
import freemarker.template.DefaultObjectWrapper;
import freemarker.template.Template;
import freemarker.template.TemplateException;

/**
 * 生成VO文件
 * 
 * @author yuebinbin
 * @date 2013-3-26
 */
public class FileGenerator {

	public void create(File file, String[][] arr) {
		Map<String, Object> map = new HashMap<String, Object>();
		map.put("className", getVoClassName(file.getName()));
		map.put("messages", getAttribute(arr[0], arr[1], arr[2]));
		map.put("key", createKEY( arr[1], arr[2], arr[3]));
		map.put("dynamicKey", createDynamicKey( arr[1], arr[2], arr[3]));
		map.put("parameter", createParameter( arr[1], arr[2], arr[3]));
		
		createHeader(file.getName(), map);
		createClass(file.getName(), map);
		//createJsonFile(file, arr);
		createCSVFile(file, arr);
	}

	/**
	 * 创建头文件
	 * 
	 * @param filename
	 * @param map
	 */
	public void createHeader(String filename, Map<String, Object> map) {
		Configuration cfg = new Configuration();
		cfg.setDefaultEncoding("UTF-8");
		cfg.setObjectWrapper(new DefaultObjectWrapper());
		try {
			cfg.setDirectoryForTemplateLoading(new File("./"
					+ ConfigManager.TEMPLATE_FOLDER_NAME));
			Template temp = cfg.getTemplate(ConfigManager.tableHeaderTemplate);
			File file = FileUtil.getLogFile(ConfigManager.classPath
					+ File.separator + getVoClassName(filename) + ".h");
			Writer out = new OutputStreamWriter(new FileOutputStream(file),
					"UTF-8");
			temp.process(map, out);
			out.flush();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (TemplateException e) {
			e.printStackTrace();
		}
	}

	/**
	 * 创建源文件cpp
	 * 
	 * @param filename
	 * @param map
	 */
	public void createClass(String filename, Map<String, Object> map) {
		Configuration cfg = new Configuration();
		cfg.setDefaultEncoding("UTF-8");
		cfg.setObjectWrapper(new DefaultObjectWrapper());
		try {
			cfg.setDirectoryForTemplateLoading(new File("./"
					+ ConfigManager.TEMPLATE_FOLDER_NAME));
			Template temp = cfg.getTemplate(ConfigManager.tableClassTemplate);
			File file = FileUtil.getLogFile(ConfigManager.classPath
					+ File.separator + getVoClassName(filename) + ".cpp");
			Writer out = new OutputStreamWriter(new FileOutputStream(file),
					"UTF-8");
			temp.process(map, out);
			out.flush();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (TemplateException e) {
			e.printStackTrace();
		}
	}

	/**
	 * 生成json文件
	 * 
	 * @param file
	 * @param arr
	 */
	public void createJsonFile(File file, String[][] arr) {

		StringBuffer sbuff = new StringBuffer("[");

		String[] type = arr[1];
		String[] name = arr[2];

		for (int i = 3; i < arr.length; i++) {
			String[] contant = arr[i];
			sbuff.append("{");
			for (int j = 0; j < type.length; j++) {
				if (isString(type[j])) {
					sbuff.append("\"").append(name[j]).append("\":\"")
							.append(contant[j]).append("\",");
				} else {
					sbuff.append("\"").append(name[j]).append("\":")
							.append(contant[j]).append(",");
				}
			}
			sbuff = new StringBuffer(sbuff.substring(0, sbuff.length() - 1));
			sbuff.append("},");
		}
		String result = sbuff.substring(0, sbuff.length() - 1) + "]";
		System.out.println(result);
		FileUtil.write(
				ConfigManager.outputPath + File.separator + getVoClassName(file.getName())
						+ ".json", result);
	}

	public void createCSVFile(File file, String[][] arr) {
		StringBuffer sbuff = new StringBuffer();

		String[] name = arr[2];
		for (int i = 0; i < name.length; i++) {
			sbuff.append(name[i]).append(",");
		}
		sbuff.append("\n");
		for (int i = 4; i < arr.length; i++) {
			String[] contant = arr[i];
			for (int j = 0; j < name.length; j++) {
				sbuff.append(contant[j]).append(",");
			}
			sbuff.append("\n");
		}
	
		PXDataGenerator.classNameList.add(file.getName());
		FileUtil.write(
				ConfigManager.outputPath + File.separator + getVoClassName(file.getName())
						+ ".csv", sbuff.toString());
	}

	/**
	 * 获得vo属性
	 * 
	 * @param title
	 * @param proList
	 * @return
	 */
	public List<AttributeVO> getAttribute(String[] titleArr, String[] proArr,
			String[] nameArr) {
		List<AttributeVO> attList = new ArrayList<AttributeVO>();
		for (int i = 0; i < nameArr.length; i++) {
			if (nameArr[i] == null || proArr[i] == null)
				continue;
			AttributeVO vo = new AttributeVO();
			vo.setComment(titleArr[i] == null ? "" : titleArr[i]);
			vo.setName(nameArr[i]);
			vo.setAttributeType(ExcelUtil.getType(proArr[i]));
			vo.setMethod(getMethod(nameArr[i], ExcelUtil.getType(proArr[i]), i));
			attList.add(vo);
		}
		return attList;
	}

	public String getMethod(String name, String type, int index) {

		String method = "getStringValue_json(rapidJsonData[i], \"data\");";

		if ("std::string".equals(type)) {
			method = "carrier.GetField(i, " + index + ", \"" + name + "\", true).c_str();";
		} else if ("int".equals(type)) {
			method = "atoi(carrier.GetField(i, " + index + ", \"" + name + "\").c_str());";
		} else if ("float".equals(type)) {
			method = "atof(carrier.GetField(i, " + index + ", \"" + name + "\").c_str());";
		} else {
			try {
				throw new Exception();
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("类型有问题！");
				return "";
			}
		}
		return method;
	}

	/**
	 * 获得VO名称
	 * 
	 * @param str
	 * @return
	 */
	public String getVoClassName(String str) {
		str = str.substring(0, str.indexOf("."));
		return str.substring(0, 1).toUpperCase() + str.substring(1);
	}

	public boolean isString(String str) {
		if ("string".equals(str)) {
			return true;
		}
		return false;
	}
	
	//创建KEY
	public String createKEY(String[] type, String[] name, String[] key) {
		StringBuffer sbuff = new StringBuffer();
		for (int i = 0; i < key.length; i++) 
		{
			if ("KEY".equals(key[i]))
			{
				if ("string".equals(type[i]))
				{
					sbuff.append("r->").append(name[i]).append(" + \"_\" + ");
				} else {
					sbuff.append("int2String(r->").append(name[i]).append(") + \"_\" + ");
				}
			}
		}
		int index = sbuff.lastIndexOf(" + \"_\" + ");
		return sbuff.substring(0, index);
	}
	
	public String createDynamicKey(String[] type, String[] name, String[] key)
	{
		StringBuffer sbuff = new StringBuffer();
		for (int i = 0; i < key.length; i++) 
		{
			if ("KEY".equals(key[i]))
			{
				if ("string".equals(type[i]))
				{
					sbuff.append(name[i]).append(" + \"_\" + ");
				} else {
					sbuff.append("int2String(").append(name[i]).append(") + \"_\" + ");
				}
			}
		}
		int index = sbuff.lastIndexOf(" + \"_\" + ");
		return sbuff.substring(0, index);
	}
	
	public String createParameter(String[] type, String[] name, String[] key)
	{
		StringBuffer sbuff = new StringBuffer();
		for (int i = 0; i < key.length; i++) 
		{
			if ("KEY".equals(key[i]))
			{
				if ("string".equals(type[i]))
				{
					sbuff.append("std::string ").append(name[i]).append(",");
				} else {
					sbuff.append("int ").append(name[i]).append(",");
				}
			}
		}
		int index = sbuff.lastIndexOf(",");
		return sbuff.substring(0, index);
	}
}
