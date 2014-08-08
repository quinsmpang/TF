package com.cyou.px.generator;

import java.io.File;

import com.cyou.px.utils.ExcelUtil;



public class ExcelDataCreator {

	public ExcelDataCreator()
	{
		super();
	}

	public void formaterData(File fis) {
		//获取excel集合:集合的第一个元素存储的为表名
		String[][] arr = ExcelUtil.convertExcel2Array(fis);
		System.out.println("make " + fis.getName() + " to VO.as files ...");
		FileGenerator vo = new FileGenerator();
		vo.create(fis, arr);
		
		//生成VO类
		System.out.println("make " + fis.getName() + " to VO.as files ...");
	}
	
	
	public static String getType(String s) {
		
		if ("int".equals(s))
		{
			return "java.lang.Integer";
		} else if ("String".equals(s)) {
			return "java.lang.String";
		} 
		return "java.lang.String";
	}
}
