package com.cyou.px.utils;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;

/**
 * 读写文件
 * @author yuebinbin
 * @date 2013-3-25
 */
public class FileUtil {

	/**
	 * 读文件
	 * */
	public static String readFile(File file) {
		StringBuffer fileContent = new StringBuffer();
		try {
			if (file.isFile() && file.exists()) {
				InputStreamReader read = new InputStreamReader(
						new FileInputStream(file), "UTF-8");
				BufferedReader reader = new BufferedReader(read);
				String line;
				while ((line = reader.readLine()) != null) {
					fileContent.append(line).append("\n");
				}
				read.close();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return String.valueOf(fileContent);
	}
	
	/**
	 * 写文件
	 * */
	public static void write(String filePath, String code){
		
		FileOutputStream ou;
		PrintStream ps;
		getLogFile(filePath);
		try{
			ou = new FileOutputStream(filePath);
			ps = new PrintStream(ou, false, "utf-8");
			ps.println(code);
			ou.close();
			ps.close();
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	
	/**
	 * @param fileName
	 * @return
	 * @throws IOException
	 */
	public static File getLogFile(String fileName) {
		File file = new File(fileName);
		if(!file.exists()) {
			List<File> tList = new ArrayList<File>();
			while(!file.exists()) {
				tList.add(file);
				file = file.getParentFile();
			}
			for(int i = tList.size() - 1; i >= 0; i--) {
				if(i > 0) {
					tList.get(i).mkdir();
				}
				if(i == 0) {
					try {
						tList.get(i).createNewFile();
					} catch (IOException e) {
						System.out.println("创建文件时出现异常。");
						e.printStackTrace();
					}
				}
			}
			file = tList.get(0);
		}
		return file;
	}
}
