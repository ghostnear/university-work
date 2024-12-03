namespace HttpDownloaderApp
{
    class Program
    {
        static async Task Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: HttpDownloaderApp <url> <fileName> <method>");
                Console.WriteLine("Methods: event-driven, task-based, async-await");
                return;
            }

            string url = args[0];
            string fileName = args[1];
            string method = args[2];

            if (method == "event-driven")
            {
                HttpDownloaderEventDriven downloader = new();
                downloader.DownloadFile(url, fileName);
                Thread.Sleep(1000); // Wait to make sure that the download ends.
                if(downloader.Result != null)
                    Console.WriteLine(downloader.Result);
                else
                    Console.WriteLine("Failed to download file.");
            }
            else if (method == "task-based")
            {
                string result = await HttpDownloaderTaskBased.DownloadFileAsync(url, fileName);
                if(result != null)
                    Console.WriteLine(result);
                else
                    Console.WriteLine("Failed to download file.");
            }
            else if (method == "async-await")
            {
                string result = await HttpDownloaderAsyncAwait.DownloadFileAsync(url, fileName);
                if(result != null)
                    Console.WriteLine(result);
                else
                    Console.WriteLine("Failed to download file.");
            }
            else
                Console.WriteLine("Unknown method: " + method);
        }
    }
}
