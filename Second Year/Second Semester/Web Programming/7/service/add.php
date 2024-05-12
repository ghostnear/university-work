<?php
    include('database.php');

    $title = $_POST['title'];
    $category = $_POST['category'];
    $contents = $_POST['contents'];
    $producer = $_POST['producer'];

    $title = mysqli_real_escape_string($connection, $title);
    $category = mysqli_real_escape_string($connection, $category);
    $contents = mysqli_real_escape_string($connection, $contents);
    $producer = mysqli_real_escape_string($connection, $producer);

    $date = date('Y-m-d');

    $title = htmlspecialchars($title);
    $category = htmlspecialchars($category);
    $contents = htmlspecialchars($contents);
    $producer = htmlspecialchars($producer);

    $title = strip_tags($title);
    $category = strip_tags($category);
    $contents = strip_tags($contents);
    $producer = strip_tags($producer);

    $title = stripslashes($title);
    $category = stripslashes($category);
    $contents = stripslashes($contents);
    $producer = stripslashes($producer);

    $title = trim($title);
    $category = trim($category);
    $contents = trim($contents);
    $producer = trim($producer);
    
    $sql = "INSERT INTO News (Title, Date, Category, Contents, Producer) VALUES ('$title', '$date', '$category', '$contents', '$producer')";

    try {
        mysqli_query($connection, $sql);
        header('Location: ../index.php');
    } catch (Exception $e) {
        $error=mysqli_error($connection);
        $backlink='../index.php';
        include('../error.php');
    }
?>