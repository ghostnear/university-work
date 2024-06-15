package webubb.domain;

public class Document {
    private int id;
    private String name;
    private String contents;

    public Document(int id, String name, String contents) {
        this.id = id;
        this.name = name;
        this.contents = contents;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getContents() {
        return contents;
    }

    public void setContents(String contents) {
        this.contents = contents;
    }
}
