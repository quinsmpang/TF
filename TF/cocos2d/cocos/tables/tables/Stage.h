#ifndef __TABLES_Stage_H__
#define __TABLES_Stage_H__
#include "cocos2d.h"
#include "TableHelper.h"

USING_NS_CC;

namespace tables
{
	class Stage_table 
	{
	public:
		//id
		int id;
		//数据
		std::string data;
		Stage_table()
		{
			memset(&id, 0, sizeof(id));
			memset(&data, 0, sizeof(data));
		}
	};

	class Stage
	{
	public:
		Stage(unsigned const char* data, size_t size);
		~Stage(void);
		std::map<int, std::unique_ptr<Stage_table>> m_data;
		static const char* fileName();
		std::string Error;
		
		Stage_table* getStageVo(
Expression parameter is undefined on line 34, column 57 in TableHeader.ftl.
The problematic instruction:
----------
==> ${parameter} [on line 34, column 55 in TableHeader.ftl]
----------

Java backtrace for programmers:
----------
freemarker.core.InvalidReferenceException: Expression parameter is undefined on line 34, column 57 in TableHeader.ftl.
	at freemarker.core.TemplateObject.assertNonNull(TemplateObject.java:124)
	at freemarker.core.Expression.getStringValue(Expression.java:118)
	at freemarker.core.Expression.getStringValue(Expression.java:93)
	at freemarker.core.DollarVariable.accept(DollarVariable.java:76)
	at freemarker.core.Environment.visit(Environment.java:208)
	at freemarker.core.MixedContent.accept(MixedContent.java:92)
	at freemarker.core.Environment.visit(Environment.java:208)
	at freemarker.core.Environment.process(Environment.java:188)
	at freemarker.template.Template.process(Template.java:237)
	at com.cyou.px.generator.FileGenerator.createHeader(FileGenerator.java:60)
	at com.cyou.px.generator.FileGenerator.create(FileGenerator.java:36)
	at com.cyou.px.generator.ExcelDataCreator.formaterData(ExcelDataCreator.java:21)
	at com.cyou.px.PXDataGenerator.getDataFiles(PXDataGenerator.java:38)
	at com.cyou.px.PXDataGenerator.getDataFiles(PXDataGenerator.java:32)
	at com.cyou.px.PXDataGenerator.getDataFiles(PXDataGenerator.java:32)
	at com.cyou.px.PXDataGenerator.getDataFiles(PXDataGenerator.java:32)
	at com.cyou.px.PXDataGenerator.run(PXDataGenerator.java:65)
	at com.cyou.px.PXDataGenerator.main(PXDataGenerator.java:95)
