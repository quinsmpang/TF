package com.cyou.px.vo;

public class AttributeVO {

	private String name;
	private String method;
	private String comment;
	private String attributeType;
	
	public String getAttributeType() {
		return attributeType;
	}
	public void setAttributeType(String attributeType) {
		this.attributeType = attributeType;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getMethod() {
		return method;
	}
	public void setMethod(String method) {
		this.method = method;
	}
	public String getComment() {
		return comment;
	}
	public void setComment(String comment) {
		this.comment = comment;
	}
}
