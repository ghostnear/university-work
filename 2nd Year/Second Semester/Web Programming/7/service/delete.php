<?php
    include('database.php');

    // There's also no permission check here. TODO: maybe make this.

    $id = $_GET['id'];      // This is the most illegal thing ever but I don't care.
    $id = mysqli_real_escape_string($connection, $id);
    $id = htmlspecialchars($id);
    $id = strip_tags($id);
    $id = stripslashes($id);
    $id = trim($id);

    $sql = "DELETE FROM News WHERE ID = " . $id;

    $result = mysqli_query($connection, $sql);

    if ($result) {
        header('Location: ../index.php');
    } else {
        echo 'Error while deleting: ' . mysqli_error($connection);
    }
?>