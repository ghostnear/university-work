<?php
if(isset($_GET["session_id"]))
    session_id($_GET["session_id"]);

include('database.php');

if(!isset($_SESSION["WeaselNews_loggedin"])){
    echo json_encode(
        array(
            "logged_in" => false,
            "message" => "You are not logged in.",
            "data" => null
        )
    );
    return;
}

echo json_encode(
    array(
        "logged_in" => true,
        "message" => "You are logged in.",
        "data" => array(
            "ID" => $_SESSION["WeaselNews_userID"],
            "username" => $_SESSION["WeaselNews_username"],
            "elevation" => $_SESSION["WeaselNews_elevation"]
        )
    )
);
?>
