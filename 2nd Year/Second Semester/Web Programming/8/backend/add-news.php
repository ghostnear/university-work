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

if(!isset($_POST['title']) || !isset($_POST['category']) || !isset($_POST['contents']))
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

if(is_null($title) || is_null($category) || is_null($contents))
{
    echo json_encode(
        array(
            "status" => "error",
            "message" => "Empty content sent to be added."
        )
    );
    return;
}

$title = mysqli_real_escape_string($connection, $title);
$category = mysqli_real_escape_string($connection, $category);
$contents = mysqli_real_escape_string($connection, $contents);

$date = date('Y-m-d');

$title = htmlspecialchars($title);
$category = htmlspecialchars($category);
$contents = htmlspecialchars($contents);

$title = strip_tags($title);
$category = strip_tags($category);
$contents = strip_tags($contents);

$title = stripslashes($title);
$category = stripslashes($category);
$contents = stripslashes($contents);

$title = trim($title);
$category = trim($category);
$contents = trim($contents);

$sql = "INSERT INTO News (Title, Date, Category, Contents, Producer) VALUES ('$title', '$date', '$category', '$contents', '" . $_SESSION['WeaselNews_userID'] . "')";

try {
    mysqli_query($connection, $sql);

    echo json_encode(
        array(
            "status" => "success",
            "message" => "News added successfully."
        )
    );
} catch (Exception $e) {
    echo json_encode(
        array(
            "status" => "error",
            "message" => "An error occurred while adding the news."
        )
    );
}
?>