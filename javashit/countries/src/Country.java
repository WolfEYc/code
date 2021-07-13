public class Country implements Comparable<Country>{

    private String code;
    private String name;
    private String area;

    public Country() {
        code = "none";
        name = "none";
        area = "0";
    }

    public Country(String code, String name, String area){
        this.code = code;
        this.name = name;
        this.area = area;
    }

    public String getCode() {
        return code;
    }
    public String getName() {
        return name;
    }
    public String getArea() {
        return area;
    }
    public void setCode(String code) {
        this.code = code;
    }
    public void setName(String name) {
        this.name = name;
    }
    public void setArea(String area) {
        this.area = area;
    }
    public String toString() {
        return code + CountryDB.sNeeded(code, 10) + name + CountryDB.sNeeded(name, 20) + area;
    }

    public int compareTo(Country c) {
        return this.name.compareTo(c.name);
    }

}