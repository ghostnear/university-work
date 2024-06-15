package webubb.domain;

public class User {
    private int id;
    private String name;
    private String authoredDocuments;
    private String authoredMovies;

    public User(int id, String username, String authoredDocuments, String authoredMovies){
        this.id = id;
        this.name = username;
        this.authoredDocuments = authoredDocuments;
        this.authoredMovies = authoredMovies;
    }

    public int getId() { return id; }

    public void setId(int id) { this.id=id; }

    public String getUsername() {
        return name;
    }

    public void setUsername(String name) {
        this.name = name;
    }

    public String getAuthoredDocuments() {
        return authoredDocuments;
    }

    public void setAuthoredDocuments(String authoredDocuments) {
        this.authoredDocuments = authoredDocuments;
    }

    public String getAuthoredMovies() {
        return authoredMovies;
    }

    public void setAuthoredMovies(String authoredMovies) {
        this.authoredMovies = authoredMovies;
    }
}