<%@ page import="webubb.domain.User" %>

<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <script src="js/jquery-2.0.3.js"></script>
    <title>Web exam please help I can't</title>
</head>
<body>
        <pre>
<%! User user; %>
<%  user = (User) session.getAttribute("user");
    if (user != null) {
        out.println("Welcome, " + user.getUsername());
        out.println("Your authored documents: " + user.getAuthoredDocuments());
        out.println("Your authored movies: " + user.getAuthoredMovies());
%></pre>
        <section>
            <u>Documents and movies (interleaved) (click on the Movie type to delete a movie):</u>
            <table id="main-table"></table>
        </section>
        <br>
        <u> Want to add a new document? </u>
        <p> Name: </p>
        <input type="text" id="newDocumentName">
        <p> Contents: </p>
        <input type="text" id="newDocumentContents">
        <br> <br>
        <button id="addDocumentButton" type="button">Add new document</button>
        <br><br>
        <u> Document with the largest number of authors: </u>
        <table id="document-table"></table>

        <script>
            function getDocuments(callbackFunction) {
                $.getJSON(
                    "DocumentsController",
                    { action: 'getAll' },
                    callbackFunction
                );
            }

            function getTopDocuments(callbackFunction) {
                $.getJSON(
                    "DocumentsController",
                    { action: 'getTop' },
                    callbackFunction
                );
            }

            function getMovies(callbackFunction) {
                $.getJSON(
                    "MoviesController",
                    { action: 'getAll' },
                    callbackFunction
                );
            }

            function addDocument(name, contents, callbackFunction) {
                $.post("DocumentsController",
                    {
                        name: name,
                        contents: contents
                    },
                    callbackFunction
                );
            }

            function deleteMovie(id) {
                $.getJSON(
                    "MoviesController",
                    { action: 'deleteOne', id: id },
                    function (response) {
                        alert(response.status);
                        constructMainTable();
                    }
                );
            }

            function constructMainTable(){
                $("#main-table").html("");
                $("#main-table").append("<tr><td>| Id </td><td>| Name / Title </td><td>| Contents / Duration </td><td> | Type |</td></tr>");

                getDocuments(function(documents) {
                    getMovies(function(movies) {
                        documents.forEach(function(document, documentIndex) {
                            $("#main-table").append("<tr><td>| " + document.id + " </td><td>| " + document.name + " </td><td>| " + document.contents + "</td><td> | Document | </td></tr>");
                            if(documentIndex < movies.length)
                                $("#main-table").append("<tr><td>| " + movies[documentIndex].id + " </td><td>| " + movies[documentIndex].title + " </td><td>| " + movies[documentIndex].duration + "</td><td onclick='deleteMovie("+ movies[documentIndex].id +")'> | Movie | </td></tr>");
                        });

                        if(movies.length > documents.length)
                            movies.forEach(function(movie, movieIndex) {
                                if(movieIndex >= documents.length)
                                    $("#main-table").append("<tr><td>| " + movies[movieIndex].id + " </td><td>| " + movies[movieIndex].title + " </td><td>| " + movies[movieIndex].duration + "</td><td onclick='deleteMovie("+ movies[movieIndex].id +")'> | Movie | </td></tr>");
                            });
                    })
                })

                $("#document-table").html("");
                $("#document-table").append("<tr><td>| Id </td><td>| Name </td><td>| Contents |</td></tr>");

                getTopDocuments(function(documents){
                    documents.forEach(function(document, documentIndex) {
                        $("#document-table").append("<tr><td>| " + document.id + " </td><td>| " + document.name + " </td><td>| " + document.contents + " |</td></tr>");
                    });
                })
            }

            $(document).ready(function() {
                constructMainTable()

                $("#addDocumentButton").click(function() {
                    addDocument($("#newDocumentName").val(), $("#newDocumentContents").val(), function(response) {
                        alert(response);
                        constructMainTable();
                    })
                    $("#newDocumentName").val("");
                    $("#newDocumentContents").val("");
                })
            });
        </script>
<%
    }
%>

</body>
</html>