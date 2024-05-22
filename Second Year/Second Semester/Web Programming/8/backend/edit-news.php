<?php
// JSON body decoding.
$_POST = json_decode(file_get_contents('php://input'), true);

if(isset($_POST["session_id"]))
    session_id($_POST["session_id"]);

include('database.php');

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

if(!isset($_POST['title']) || !isset($_POST['category']) || !isset($_POST['contents']) || !isset($_POST['date']) || !isset($_POST['id']))
{
    echo json_encode(
        array(
            "status" => "error",
            "message" => "Invalid content sent to be added."
        )
    );
    return;
}

$title = $_POST['title'];
$category = $_POST['category'];
$contents = $_POST['contents'];
$date = $_POST['date'];
$id = $_POST['id'];

if(empty($title) || empty($category) || empty($contents) || empty($date) || empty($id))
{
    echo json_encode(
        array(
            "status" => "error",
            "message" => "Empty content sent to be edited."
        )
    );
    return;
}

$title = mysqli_real_escape_string($connection, $title);
$category = mysqli_real_escape_string($connection, $category);
$contents = mysqli_real_escape_string($connection, $contents);
$date = mysqli_real_escape_string($connection, $date);
$id = mysqli_real_escape_string($connection, $id);

$title = htmlspecialchars($title);
$category = htmlspecialchars($category);
$contents = htmlspecialchars($contents);
$date = htmlspecialchars($date);
$id = htmlspecialchars($id);

$title = strip_tags($title);
$category = strip_tags($category);
$contents = strip_tags($contents);
$date = strip_tags($date);
$id = strip_tags($id);

$title = stripslashes($title);
$category = stripslashes($category);
$contents = stripslashes($contents);
$date = stripslashes($date);
$id = stripslashes($id);

$title = trim($title);
$category = trim($category);
$contents = trim($contents);
$date = trim($date);
$id = trim($id);

$sql = "UPDATE News SET Title = '" . $title . "', Category = '" . $category . "', Contents = '" . $contents . "', Date = '" . $date . "' WHERE ID = " . $id;

try {
    mysqli_query($connection, $sql);

    echo json_encode(
        array(
            "status" => "success",
            "message" => "News edited successfully."
        )
    );
} catch (Exception $e) {
    echo json_encode(
        array(
            "status" => "error",
            "message" => "An error occurred while editing the news."
        )
    );
}
?>