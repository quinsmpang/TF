package com.cyou.px;

import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import java.util.List;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

public class ConfigManager {

	public static ConfigManager instance;
	//public static String FILEXML_PATH = "input" + File.separator + File.separator + "resource" + File.separator + "config" + File.separator + "compressFile.xml";
	/** 配置文件config位置*/
	public static String CONFIG_PATH = "config";
	/** 模板文件存储位置  */
	public static String TEMPLATE_FOLDER_NAME = "template";
	
	public static String inputPath = null;
	public static String outputPath = null;

	public static String classPath = null;
	
	
	/** TableClass模板 */
	public static String tableClassTemplate = "TableClass.ftl";
	/**TableHeader模板*/
	public static String tableHeaderTemplate = "TableHeader.ftl"; 
	
	/** TableClass模板 */
	public static String managerHeaderTemplate = "ManagerHeader.ftl";
	/**TableHeader模板*/
	public static String managerClassTemplate = "ManagerClass.ftl"; 

	public static ConfigManager getInstance() {
		if (instance == null) {
			instance = new ConfigManager();
		}
		return instance;
	}
	
	@SuppressWarnings("unchecked")
	public void init() {
		File xmlFile;
		try {
			xmlFile = new File("./" + CONFIG_PATH + File.separator + "config.xml").getCanonicalFile();
		} catch (IOException e1) {
			e1.printStackTrace();
			return;
		}
		SAXReader reader = new SAXReader();
		Document xmlDoc;
		try {
			xmlDoc = reader.read(xmlFile);
			Element root = xmlDoc.getRootElement();
			List<Element> listRowSet = root.elements();
			for (Iterator<Element> i = listRowSet.iterator(); i.hasNext();) {
				Element ele = i.next();
				String temp = ele.getName();
				if ("input".equals(temp))
				{
					inputPath = ele.attributeValue("path");
					try {
						inputPath = new File("./" + inputPath).getCanonicalFile().getPath() + File.separator;
					} catch (IOException e) {
					}
					continue;
				}else if ("output".equals(temp))
				{
					outputPath = ele.attributeValue("path");
					classPath = ele.attributeValue("classPath");
					try {
						outputPath = new File("./" + outputPath).getCanonicalFile().getPath() + File.separator;
						classPath = new File("./" + classPath).getCanonicalFile().getPath() + File.separator;
					} catch (IOException e) {
					}
					continue;
				}
				
			}
		} catch (DocumentException e) {
			e.printStackTrace();
		}
	}
}
