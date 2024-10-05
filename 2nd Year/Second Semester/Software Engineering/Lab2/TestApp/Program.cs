using Logging;

namespace TestApp
{
    internal class Program
    {
        static void Main(string[] args)
        {
            // Console writer example demonstrates buffering.
            ConsoleLogger logger = new ConsoleLogger();
            
            logger.log(LogLevel.INFO, "Hello, World 3!");
            logger.log(LogLevel.WARNING, "This is a warning.");
            logger.log(LogLevel.ERROR, "This is an error.");

            Console.WriteLine("Hello, World!");

            logger.log(LogLevel.FATAL, "This is a fatal error.");
            logger.log(LogLevel.DEBUG, "This is a debugging message");

            Console.WriteLine("Hello, World 2!");

            // File writer example demonstrates file working.
            FileLogger fileLogger = new FileLogger("log.txt");

            fileLogger.log(LogLevel.INFO, "Hello, World 3!");
            fileLogger.log(LogLevel.WARNING, "This is a warning.");
            fileLogger.log(LogLevel.ERROR, "This is an error.");
        }
    }
}
