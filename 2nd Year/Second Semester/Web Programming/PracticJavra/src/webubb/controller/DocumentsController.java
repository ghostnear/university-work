package webubb.controller;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import webubb.domain.Document;
import webubb.model.DBManager;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;


public class DocumentsController extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String action = request.getParameter("action");

        if(action == null)
            return;

        if (action.equals("getAll")) {
            response.setContentType("application/json");
            DBManager dbmanager = new DBManager();
            ArrayList<Document> documents = dbmanager.getDocuments();
            JSONArray jsonDocuments = new JSONArray();
            for (Document document : documents) {
                JSONObject jsonObject = new JSONObject();
                jsonObject.put("id", document.getId());
                jsonObject.put("name", document.getName());
                jsonObject.put("contents", document.getContents());
                jsonDocuments.add(jsonObject);
            }
            PrintWriter out = new PrintWriter(response.getOutputStream());
            out.println(jsonDocuments.toJSONString());
            out.flush();
        }

        if (action.equals("getTop")) {
            response.setContentType("application/json");
            DBManager dbmanager = new DBManager();
            ArrayList<Document> documents = dbmanager.getTopDocument();
            JSONArray jsonDocuments = new JSONArray();
            for (Document document : documents) {
                JSONObject jsonObject = new JSONObject();
                jsonObject.put("id", document.getId());
                jsonObject.put("name", document.getName());
                jsonObject.put("contents", document.getContents());
                jsonDocuments.add(jsonObject);
            }
            PrintWriter out = new PrintWriter(response.getOutputStream());
            out.println(jsonDocuments.toJSONString());
            out.flush();
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String documentName = request.getParameter("name");
        String documentContents = request.getParameter("contents");
        DBManager dbmanager = new DBManager();
        boolean result = dbmanager.addDocument(documentName, documentContents);
        PrintWriter out = new PrintWriter(response.getOutputStream());
        if (result)
            out.println("Document added successfully!");
        else
            out.println("Could not add the document.");
        out.flush();
    }
}
