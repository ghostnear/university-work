<?php
    include('database.php');

    $id = $_POST['id'];
    $id = mysqli_real_escape_string($connection, $id);
    $id = htmlspecialchars($id);
    $id = strip_tags($id);
    $id = stripslashes($id);
    $id = trim($id);

    $title = $_POST['title'];
    $title = mysqli_real_escape_string($connection, $title);
    $title = htmlspecialchars($title);
    $title = strip_tags($title);
    $title = stripslashes($title);
    $title = trim($title);

    $date = $_POST['date'];
    $date = mysqli_real_escape_string($connection, $date);
    $date = htmlspecialchars($date);
    $date = strip_tags($date);
    $date = stripslashes($date);
    $date = trim($date);

    $category = $_POST['category'];
    $category = mysqli_real_escape_string($connection, $category);
    $category = htmlspecialchars($category);
    $category = strip_tags($category);
    $category = stripslashes($category);
    $category = trim($category);

    $contents = $_POST['contents'];
    $contents = mysqli_real_escape_string($connection, $contents);
    $contents = htmlspecialchars($contents);
    $contents = strip_tags($contents);
    $contents = stripslashes($contents);
    $contents = trim($contents);

    $sql = "UPDATE News SET Title = '" . $title . "', Date = '" . $date . "', Category = '" . $category . "', Contents = '" . $contents . "' WHERE ID = " . $id;

    try {
        mysqli_query($connection, $sql);
        header('Location: ../news.php?id=' . $id);
    } catch (Exception $e) {
        $error=mysqli_error($connection);
        $backlink='../news.php?id=' . $id;
        include('../error.php');
    }
?>