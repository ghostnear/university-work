<?php $title='Home | Weasel News'; include("template/top.php");?>

<?php include("component/genericheader.php");?>

<main class="w-5/6 h-full mx-auto flex justify-center flex-col">

    <h1 class="text-4xl font-bold text-center mb-10"> Select what you want to see: </h1>

    <form class="bg-slate-900 rounded-md w-1/2 mx-auto p-5" action="index.php" method="POST">
        <h2 class="text-2xl mb-3">Category:</h2>
        <select class="bg-slate-800 w-full p-3 mb-3" name="category" selected="">
            <option value="">None</option>
            <?php
                include('service/database.php');

                $sql = "SELECT DISTINCT Category FROM News";

                $result = mysqli_query($connection, $sql);

                if (mysqli_num_rows($result) > 0) {
                    while($row = mysqli_fetch_assoc($result)) {
                        echo '<option value="' . $row['Category'] . '">' . $row['Category'] . '</option>';
                    }
                }
            ?>
        </select>
        <h2 class="text-2xl mb-3">Starting date:</h2>
        <input type="date" class="w-full bg-slate-700 p-3 rounded-md mb-3" name="date-start" value=""></input>
        <h2 class="text-2xl mb-3">Ending date:</h2>
        <input type="date" class="w-full bg-slate-700 p-3 rounded-md mb-3" name="date-end" value=""></input>
        <input type="submit" class="w-full h-12 bg-slate-700 hover:bg-slate-600 rounded-md text-white text-lg mt-3" value="Filter">
    </form>

    <a class="text-2xl hover:underline font-bold text-center mt-10" href="index.php"> Or go back by clicking here.. </a>
</main>

<?php include("template/bottom.php");?>