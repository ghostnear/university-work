<?php $title='Article | Weasel News'; include("template/top.php");?>

<?php include("component/genericheader.php");?>

<main class="w-5/6 h-full mx-auto flex justify-center flex-col">
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

            echo '<div class="flex flex-col border-b border-gray-400 pb-6">';
                echo '<div class="flex">';
                    echo '<a class="text-4xl font-bold">' . $row['Title'] . '</a>';   
                    echo '<span class="ml-auto text-sm">' . $row['Date'] . '</span>';
                echo '</div>';
                
                echo '<span class="text-sm my-auto"> posted in ' . $row['Category'] . ' by ' . $rowUser['Username'] . '</span>';

                echo '<div class="mt-4">' . $row['Contents'] . '</div>';
            echo '</div>';

            if (isset($_SESSION['WeaselNews_loggedin']) && $_SESSION['WeaselNews_loggedin'] == true && ($_SESSION['WeaselNews_userID'] == $row['Producer'] || $_SESSION['WeaselNews_elevation'] == 1)) {
                echo '<div class="ml-auto mt-4">';
                    echo '<a class="text-2xl hover:text-emerald-700 text-emerald-400" href="edit-news.php?id=' . $row['ID'] . '"> Edit </a>';
                    echo '<a class="ml-4 text-2xl hover:text-red-900 text-red-500" onclick="document.getElementById(`deleteModal`).classList.remove(`hidden`);"> Delete </a>';
                echo '</div>';
            }
        }
    } else {
        include("component/404.php");
    }
?>
</main>

<!-- Delete modal -->
<div class="fixed z-10 inset-0 hidden" id="deleteModal">
    <div class="w-full h-full flex bg-opacity-50 bg-black">
        <div class="w-1/2 h-1/2 bg-slate-900 rounded-lg shadow-lg mx-auto my-auto">
            <div class="w-full h-full flex">
                <div class="mx-auto my-auto">
                    <h1 class="text-3xl"> Are you sure you want to delete this article? </h1>
                    <div class="flex mt-4">
                        <a class="text-2xl hover:bg-emerald-600 rounded-md bg-emerald-400 w-1/2 p-3 px-5 text-center" href="service/delete.php?id=<?php echo $id; ?>"> Yes </a>
                        <a class="ml-4 text-2xl hover:bg-red-800 rounded-md bg-red-500 w-1/2 p-3 px-5 text-center" onclick="document.getElementById(`deleteModal`).classList.add(`hidden`);"> No </a>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>

<?php include("template/bottom.php");?>