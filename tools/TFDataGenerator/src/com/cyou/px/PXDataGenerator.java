package com.cyou.px;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.cyou.px.generator.ExcelDataCreator;
import com.cyou.px.utils.FileUtil;
import com.cyou.px.vo.AttributeVO;

import freemarker.template.Configuration;
import freemarker.template.DefaultObjectWrapper;
import freemarker.template.Template;
import freemarker.template.TemplateException;

public class PXDataGenerator {
	
	public static List<String> classNameList = new ArrayList<String>();
	
	//获得excel文件
	public void getDataFiles(File file) {
		if (file.isHidden()) return;
		if (file.isDirectory()) {
			File[] f = file.listFiles();
			for (File fs:f) {
				getDataFiles(fs);
			}
		} else {
			ExcelDataCreator excel = new ExcelDataCreator();
			excel.formaterData(file);
		}
	}
	
	//生成DataManager
	public void createDataManager(Map<String, Object> map, String template, String filename)
	{
		Configuration cfg = new Configuration();
		cfg.setDefaultEncoding("UTF-8");
		cfg.setObjectWrapper(new DefaultObjectWrapper());
		try {
			cfg.setDirectoryForTemplateLoading(new File("./" + ConfigManager.TEMPLATE_FOLDER_NAME));
			Template temp = cfg.getTemplate(template);
			File file = FileUtil.getLogFile(ConfigManager.classPath + File.separator  + filename);
			Writer out = new OutputStreamWriter(new FileOutputStream(file), "UTF-8");
			temp.process(map, out);
			out.flush();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (TemplateException e) {
			e.printStackTrace();
		}
	}
	
	public void run()
	{
		getDataFiles(new File(ConfigManager.inputPath));
		
		Map<String, Object> map = new HashMap<String, Object>();
		map.put("fileSize", classNameList.size());
		
		List<AttributeVO> attList = new ArrayList<AttributeVO>();
		for(int i = 0; i < classNameList.size(); i++) {
			AttributeVO vo = new AttributeVO();
			vo.setName(getVoClassName(classNameList.get(i)));
			vo.setAttributeType(getVoClassName(classNameList.get(i)).toUpperCase());
			attList.add(vo);
		}
		map.put("messages", attList);
		
		createDataManager(map, ConfigManager.managerHeaderTemplate, "DataManager.h");
		createDataManager(map, ConfigManager.managerClassTemplate, "DataManager.cpp");
	}
	
	public String getVoClassName(String str) {
		str = str.substring(0, str.indexOf("."));
		return str.substring(0, 1).toUpperCase() + str.substring(1);
	}

	public static void main(String[] args) {
		
		//初始化配置文件
		ConfigManager.getInstance().init();
		
		PXDataGenerator px = new PXDataGenerator();
		
		px.run();
		
	}
	
	
}
