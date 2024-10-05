<?php $title='Edit Article | Weasel News'; include("template/top.php");?>

<?php include("component/genericheader.php");?>

<main class="w-1/2 h-full mx-auto flex justify-center flex-col">
<?php
    include('service/database.php');

    $id = $_GET['id'];
    $id = mysqli_real_escape_string($connection, $id);
    $id = htmlspecialchars($id);
    $id = strip_tags($id);
    $id = stripslashes($id);
    $id = trim($id);

    $sql = "SELECT * FROM News WHERE ID = " . $id;

    $result = mysqli_query($connection, $sql);

    if (mysqli_num_rows($result) > 0) {
        while($row = mysqli_fetch_assoc($result)) {
            $sqlUser = "SELECT * FROM Users WHERE ID = " . $row['Producer'];

            $resultUser = mysqli_query($connection, $sqlUser);
            $rowUser = mysqli_fetch_assoc($resultUser);

            echo '<h1 class="mx-auto text-4xl mb-3 font-bold">Edit Article</h1>';

            echo '<form class="flex flex-col pb-6" action="service/edit.php" method="POST">';
                echo '<input type="hidden" name="id" value="' . $row['ID'] . '">';

                echo '<label class="text-2xl mb-2" for="title">Title:</label>';
                echo '<input type="text" name="title" class="bg-slate-800 text-md border border-slate-600 hover:border-white p-2 rounded-md mb-3" value="' . $row['Title'] . '">';
                
                echo '<label class="text-2xl mb-2" for="date">Date:</label>';
                echo '<input type="text" name="date" class="bg-slate-800 text-md border border-slate-600 hover:border-white p-2 rounded-md mb-3" value="' . $row['Date'] . '">';
                
                echo '<label class="text-2xl mb-2" for="category">Category:</label>';
                echo '<input type="text" name="category" class="bg-slate-800 text-md border border-slate-600 hover:border-white p-2 rounded-md mb-3" value="' . $row['Category'] . '">';
                
                echo '<label class="text-2xl mb-2" for="contents">Contents:</label>';
                echo '<textarea class="bg-slate-800 rounded-md border border-slate-600 hover:border-white p-3 mb-4" name="contents">' . $row['Contents'] . '</textarea>';
                
                echo '<input type="submit" class="hover:cursor-pointer bg-slate-800 mx-auto w-1/2 p-3 rounded-md active:bg-slate-600 border border-slate-600 hover:border-white" value="Submit Changes">';
            echo '</form>';
        }
    }
    else {
        include("component/404.php");
    }
?>
</main>

<?php include("template/bottom.php");?>