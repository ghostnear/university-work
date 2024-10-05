<?php
include('database.php');

$_SESSION["WeaselNews_loggedin"] = false;
$_SESSION["WeaselNews_username"] = "";
$_SESSION["WeaselNews_elevation"] = 0;
$_SESSION["WeaselNews_userID"] = 0;

echo json_encode(
    array(
        "logged_in" => false,
        "message" => "Logged out sucessfully.",
        "data" => null
    )
);
?>
