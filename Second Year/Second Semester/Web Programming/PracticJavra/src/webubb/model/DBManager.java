package webubb.model;

import webubb.domain.Movie;
import webubb.domain.Document;
import webubb.domain.User;

import java.sql.*;
import java.util.ArrayList;

public class DBManager {
    private Statement statement;

    public DBManager() {
        connect();
    }

    public void connect() {
        try {
            Class.forName("org.gjt.mm.mysql.Driver");
            Connection con = DriverManager.getConnection(
                    "jdbc:mysql://localhost/authorsdb",
                    "root",
                    "");
            statement = con.createStatement();
        } catch(Exception error) {
            System.out.println("Error during the creation of the database connection:"+error.getMessage());
            error.printStackTrace();
        }
    }

    public User authenticate(String name, String document) {
        ResultSet resultSet;
        User user = null;
        try {
            resultSet = statement.executeQuery("select * from authors where name='" + name + "' and (documentlist LIKE '%"+document+"%' or movielist LIKE '%" + document + "%')");
            if (resultSet.next()) {
                user = new User(
                        resultSet.getInt("id"),
                        resultSet.getString("name"),
                        resultSet.getString("documentlist"),
                        resultSet.getString("movielist")
                );
            }
            resultSet.close();
        } catch (SQLException error) {
            error.printStackTrace();
        }
        return user;
    }

    public ArrayList<Document> getDocuments() {
        ArrayList<Document> topics = new ArrayList<Document>();
        ResultSet resultSet;
        try {
            resultSet = statement.executeQuery("select * from documents");
            while (resultSet.next()) {
                topics.add(new Document(
                        resultSet.getInt("id"),
                        resultSet.getString("name"),
                        resultSet.getString("contents")
                ));
            }
            resultSet.close();
        } catch (SQLException error) {
            error.printStackTrace();
        }
        return topics;
    }

    public ArrayList<Document> getTopDocument() {
        ArrayList<Document> topics = new ArrayList<Document>();
        ResultSet resultSet;
        try {
            resultSet = statement.executeQuery("select * from documents limit 1");
            while (resultSet.next()) {
                topics.add(new Document(
                        resultSet.getInt("id"),
                        resultSet.getString("name"),
                        resultSet.getString("contents")
                ));
            }
            resultSet.close();
        } catch (SQLException error) {
            error.printStackTrace();
        }
        return topics;
    }

    public boolean addDocument(String documentName, String documentContents) {
        int result = 0;
        try {
            result = statement.executeUpdate("insert into documents (name, contents) values ('" + documentName + "','" + documentContents + "')");
        } catch (SQLException error) {
            error.printStackTrace();
        }
        if (result > 0) {
            return true;
        } else {
            return false;
        }
    }

    public boolean deleteMovie(int movieID) {
        int result = 0;
        try {
            // TODO: update movielist from session user.
            result = statement.executeUpdate("delete from movies where id=" + movieID);
        } catch (SQLException error) {
            error.printStackTrace();
        }
        if (result > 0) {
            return true;
        } else {
            return false;
        }
    }

    public ArrayList<Movie> getMovies() {
        ArrayList<Movie> movies = new ArrayList<>();
        ResultSet rs;
        try {
            rs = statement.executeQuery("select * from movies");
            while (rs.next()) {
                movies.add(new Movie(
                    rs.getInt("id"),
                    rs.getString("title"),
                    rs.getInt("duration")
                ));
            }
            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return movies;
    }
}