package webubb.controller;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import webubb.domain.Document;
import webubb.domain.Movie;
import webubb.model.DBManager;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;

public class MoviesController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");

        if(action == null)
            return;

        if (action.equals("getAll")) {
            response.setContentType("application/json");
            DBManager dbmanager = new DBManager();
            ArrayList<Movie> movies = dbmanager.getMovies();
            JSONArray jsonMovies = new JSONArray();
            for (Movie movie : movies) {
                JSONObject jsonObject = new JSONObject();
                jsonObject.put("id", movie.getId());
                jsonObject.put("title", movie.getTitle());
                jsonObject.put("duration", movie.getDuration());
                jsonMovies.add(jsonObject);
            }
            PrintWriter out = new PrintWriter(response.getOutputStream());
            out.println(jsonMovies.toJSONString());
            out.flush();
        }

        if (action.equals("deleteOne"))
        {
            int movieID = Integer.parseInt(request.getParameter("id"));
            DBManager dbmanager = new DBManager();
            boolean result = dbmanager.deleteMovie(movieID);
            JSONObject resultJSON = new JSONObject();
            if (result)
                resultJSON.put("status", "Movie deleted successfully.");
            else
                resultJSON.put("status", "Could not delete the movie.");
            PrintWriter out = new PrintWriter(response.getOutputStream());
            out.println(resultJSON.toJSONString());
            out.flush();
        }
    }
}
