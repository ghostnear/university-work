<?php $title='Task'; include("template/top.php");?>

<main class="w-5/6 h-full mx-auto flex justify-center flex-col">
    <div class="p-4 border-b">
        <pre>
In this lab you will have to develop a server-side web application in PHP.

The web application has to manipulate a MYSQL database with 1 to 3 tables
    and should implement the following base operations on these tables: select, insert, delete, update.

Also the web application must use AJAX for getting data asynchronously from the web server
    and the web application should contain at least 5 web pages (client-side html or server-side php).

Please make sure that you avoid sql-injection attacks when working with the database.
        </pre>
        <pre>
Have in mind the user experience when you implement the problem:
    add different validation logic for input fields
    do not force the user to input an ID for an item if he wants to delete/edit/insert it;
        this should happen automatically (e.g. the user clicks an item from a list,
        and a page/modal prepopulated with the data for that particular item is opened, where the user can edit it)
    add confirmation when the user deletes/cancels an item
    do a bare minimum CSS that at least aligns the various input fields
        </pre>
        <pre>
Write a web application for a news service.
News are saved on a database and they have the following characteristics:
    text of the news, title, producer, date, category (politics, society, health etc.).

Some users add or update news and others just view news.
The user who adds or updates news must log in using a username and password before doing this.
The other type of users can see all the news from a range of dates and all news from a specific category (use AJAX for these filters).
Also, on the news browsing page, the filter used for the previous browsing action (i.e. date range, category), should be displayed in JS. 
        </pre>
    </div>
    <div class="p-4 flex justify-center">
        <a class="text-2xl hover:underline" href="index.php"> Back to index </a>
    </div>
</main>

<?php include("template/bottom.php");?>