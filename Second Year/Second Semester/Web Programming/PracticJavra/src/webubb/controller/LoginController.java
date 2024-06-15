package webubb.controller;

import java.io.IOException;
import java.util.Objects;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import webubb.model.DBManager;
import webubb.domain.User;



public class LoginController extends HttpServlet {
    User currentUser = null;
    public LoginController() {
        super();
    }

    protected void doPost(HttpServletRequest request,
                          HttpServletResponse response) throws ServletException, IOException {

        String name = request.getParameter("name");
        String document = request.getParameter("document");
        RequestDispatcher rd = null;

        DBManager dbmanager = new DBManager();
        User user = dbmanager.authenticate(name, document);
        if (user != null) {
            currentUser = user;
            rd = request.getRequestDispatcher("/succes.jsp");
            //request.setAttribute("user", user);
            // Here we should set the "user" attribute on the session like this:
            HttpSession session = request.getSession();
            session.setAttribute("user", user);
            // ... and then, in all JSP/Servlet pages we should check if the "user" attribute exists in the session
            // and if not, we should return/exit the method:
            // HttpSession session = request.getSession();
            // String user = session.getAttribute("user");
            // if (user==null || user.equals("")) {
            //        return;
            // }
        } else {
            rd = request.getRequestDispatcher("/error.jsp");
        }
        rd.forward(request, response);
        response.sendRedirect("/MyDreamsServlet");
    }

    protected void doGet(HttpServletRequest request,
                          HttpServletResponse response) throws ServletException, IOException {
        String destination = request.getParameter("destination");
        RequestDispatcher rd = null;
        if (Objects.equals(destination, "seeTopic")) {
            rd = request.getRequestDispatcher("/topicView.jsp");
            HttpSession session = request.getSession();
            session.setAttribute("user", currentUser);
        } else {
            rd = request.getRequestDispatcher("/error.jsp");
        }
        rd.forward(request, response);
        response.sendRedirect("/RoutesController");
    }

}