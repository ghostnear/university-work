<?php

// JSON body decoding.
$_POST = json_decode(file_get_contents('php://input'), true);

if(isset($_POST["session_id"]))
    session_id($_POST["session_id"]);

include('database.php');

// Check if the user is logged in.
if(!isset($_SESSION['WeaselNews_userID']))
{
    echo json_encode(
        array(
            "status" => "error",
            "message" => "Not logged in."
        )
    );
    return;
}

if(!isset($_POST['id']) || empty($_POST['id'])) {
    echo json_encode(
        array(
            "status" => "error",
            "message" => "Article ID is required."
        )
    );
    return;
}

$id = $_POST['id'];
$id = mysqli_real_escape_string($connection, $id);
$id = htmlspecialchars($id);
$id = strip_tags($id);
$id = stripslashes($id);
$id = trim($id);

$sql = "DELETE FROM News WHERE ID = " . $id;

$result = mysqli_query($connection, $sql);

if ($result) {
    echo json_encode(
        array(
            "status" => "success",
            "message" => "Article deleted successfully."
        )
    );
} else {
    echo json_encode(
        array(
            "status" => "error",
            "message" => "Error while deleting article: " . mysqli_error($connection) . "."
        )
    );
}
?>