#include "Stage.h"

#define KEY 
Expression key is undefined on line 3, column 15 in TableClass.ftl.
The problematic instruction:
----------
==> ${key} [on line 3, column 13 in TableClass.ftl]
----------

Java backtrace for programmers:
----------
freemarker.core.InvalidReferenceException: Expression key is undefined on line 3, column 15 in TableClass.ftl.
	at freemarker.core.TemplateObject.assertNonNull(TemplateObject.java:124)
	at freemarker.core.Expression.getStringValue(Expression.java:118)
	at freemarker.core.Expression.getStringValue(Expression.java:93)
	at freemarker.core.DollarVariable.accept(DollarVariable.java:76)
	at freemarker.core.Environment.visit(Environment.java:208)
	at freemarker.core.MixedContent.accept(MixedContent.java:92)
	at freemarker.core.Environment.visit(Environment.java:208)
	at freemarker.core.Environment.process(Environment.java:188)
	at freemarker.template.Template.process(Template.java:237)
	at com.cyou.px.generator.FileGenerator.createClass(FileGenerator.java:87)
	at com.cyou.px.generator.FileGenerator.create(FileGenerator.java:37)
	at com.cyou.px.generator.ExcelDataCreator.formaterData(ExcelDataCreator.java:21)
	at com.cyou.px.PXDataGenerator.getDataFiles(PXDataGenerator.java:38)
	at com.cyou.px.PXDataGenerator.getDataFiles(PXDataGenerator.java:32)
	at com.cyou.px.PXDataGenerator.getDataFiles(PXDataGenerator.java:32)
	at com.cyou.px.PXDataGenerator.getDataFiles(PXDataGenerator.java:32)
	at com.cyou.px.PXDataGenerator.run(PXDataGenerator.java:65)
	at com.cyou.px.PXDataGenerator.main(PXDataGenerator.java:95)
