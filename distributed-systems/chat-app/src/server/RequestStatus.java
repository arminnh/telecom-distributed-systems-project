/**
 * Autogenerated by Avro
 * 
 * DO NOT EDIT DIRECTLY
 */
package server;  
@SuppressWarnings("all")
@org.apache.avro.specific.AvroGenerated
public enum RequestStatus { 
  PENDING, ACCEPTED, DECLINED, DELETED  ;
  public static final org.apache.avro.Schema SCHEMA$ = new org.apache.avro.Schema.Parser().parse("{\"type\":\"enum\",\"name\":\"RequestStatus\",\"namespace\":\"server\",\"symbols\":[\"PENDING\",\"ACCEPTED\",\"DECLINED\",\"DELETED\"]}");
  public static org.apache.avro.Schema getClassSchema() { return SCHEMA$; }
}
