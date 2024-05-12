<?php
// Database data.
$servername = "localhost";
$username = "root";
$password = ""; 
$dbname = "WeaselNews";

// Database connection.
$connection = new mysqli($servername, $username, $password, $dbname);

// Check connection.
if(mysqli_connect_errno()) {  
    die("Failed to connect with MySQL: ". mysqli_connect_error());  
}

session_start();
?>