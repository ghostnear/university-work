<div class="border w-1/2 mx-auto p-4 rounded-md">
    <h1 class="text-3xl mt-2"> Login </h1>

    <div class="border-b my-3"></div>

    <?php
        if (isset($_SESSION['WeaselNews_loggedinerror'])) {
            echo "<div class='bg-red-500 text-white mb-3 p-3 rounded-md'>" . $_SESSION['WeaselNews_loggedinerror'] . "</div>";
            unset($_SESSION['WeaselNews_loggedinerror']);
        }
    ?>

    <form name="loginform" class="flex justify-center flex-col" method="POST" action="service/connect.php">
        <div class="mb-3">
            <label class="text-xl" for="username">Username:</label>
            <input class="w-full p-3 text-gray-100 bg-gray-700 mb-3" id="username" name="username">
        </div>
        
        <div class="mb-3">
            <label class="text-xl" for="password">Password:</label>
            <input class="w-full p-3 text-gray-100 bg-gray-700 mb-3" id="password" name="password" type="password">
        </div>

        
        <input class="bg-gray-600 w-1/2 p-3 rounded-md hover:bg-gray-500 mx-auto" type="submit" value="Connect">
    </form>
</div>