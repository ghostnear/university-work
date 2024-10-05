<?php $title='Home | Weasel News'; include("template/top.php");?>

<?php include("component/genericheader.php");?>

<main class="w-5/6 h-full mx-auto flex justify-center flex-col">
<?php
    if (isset($_SESSION['WeaselNews_loggedin']) && $_SESSION['WeaselNews_loggedin'] == true) {
        if(!isset($_POST["category"]) && !isset($_POST["date-start"]) && !isset($_POST["date-end"]))
        {
            echo "<div class='flex justify-center items-center w-full h-12 bg-slate-900 shadow-sm rounded-t-md text-white text-lg font-bold'>Welcome, " . $_SESSION['WeaselNews_username'] . " let's have a look at the news:" . "</div>";
            echo "<a class='w-full hover:underline h-12 bg-slate-900 rounded-b-md shadow-sm text-white text-lg px-4 mb-3' href='filter.php'>Filter these articles.</a>";
            include("component/newslist.php");
        }
        else {
            include('service/database.php');

            $category = $_POST["category"];
            $dateStart = $_POST["date-start"];
            if($dateStart == "")
                $dateStart = "1970-01-01";
            $dateEnd = $_POST["date-end"];
            if($dateEnd == "")
                $dateEnd = date("Y-m-d", time());

            if($category != "")
            {
                echo '<span class="text-lg">Filtering by category: ' . $category . '</span>';
            }
            if($dateStart != "1970-01-01")
            {
                echo '<span class="text-lg">Filtering by date start: ' . $dateStart . '</span>';
            }
            if($dateEnd != date("Y-m-d", time()))
            {
                echo '<span class="text-lg">Filtering by date end: ' . $dateEnd . '</span>';
            }
            
            if($category == "") {
                $sql = "SELECT * FROM News WHERE Date BETWEEN '$dateStart' AND '$dateEnd' ORDER BY Date DESC";
            }
            else {
                $sql = "SELECT * FROM News WHERE Category = '$category' AND Date BETWEEN '$dateStart' AND '$dateEnd' ORDER BY Date DESC";
            }
        
            $result = mysqli_query($connection, $sql);
        
            if (mysqli_num_rows($result) > 0) {
                while($row = mysqli_fetch_assoc($result)) {
                    $sqlUser = "SELECT * FROM Users WHERE ID = " . $row['Producer'];
        
                    $resultUser = mysqli_query($connection, $sqlUser);
                    $rowUser = mysqli_fetch_assoc($resultUser);
        
                    echo '<div class="flex flex-col border-b border-gray-400 py-4">';
                    echo '<div class="flex">';
                    echo '<a class="text-2xl hover:underline font-bold" href="news.php?id=' . $row['ID'] . '">' . $row['Title'] . '</a>';
                    echo '<div class="text-sm my-auto ml-2"> posted in ' . $row['Category'] . '</div>';
                    echo '<div class="ml-auto text-sm">' . $row['Date'] . '</div>';
                    echo '</div>';
                    echo '<div class="text-sm"> By ' . $rowUser['Username'] . '</div>';
                    echo '</div>';
                }
            } else {
                echo '<div class="text-2xl text-center"> No news available. </div>';
            }

            echo "<a class='w-full hover:underline text-center text-white text-lg mt-4' href='index.php'>Go back to all news.</a>";
        }
    } else {
        include("component/login.php");
    }
?>
</main>

<?php include("template/bottom.php");?>