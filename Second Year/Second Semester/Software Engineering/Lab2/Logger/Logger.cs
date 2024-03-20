namespace Logging
{
    public enum LogLevel
    {
        DEBUG = 0,
        INFO,
        WARNING,
        ERROR,
        FATAL
    }

    public abstract class Logger
    {
        protected string[] logBuffer;
        protected int logBufferSize, logPosition = 0;

        public Logger(int bufferSize = 3)
        {
            logBufferSize = bufferSize;
            logBuffer = new string[logBufferSize];
        }

        ~Logger()
        {
            flush();
        }

        protected string buildFlushableString()
        {
            string flushableString = "";
            for (int index = 0; index < logPosition; index++)
                flushableString += logBuffer[index];
            return flushableString;
        }

        private static string getCurrentDate()
        {
            return DateTime.Now.ToString(@"dd\/MM\/yyyy hh\:mm tt");
        }

        public void log(LogLevel level, string message)
        {
            logBuffer[logPosition++] = $"[{getCurrentDate()}] [{level}]: {message}\n";
            if (logPosition == logBufferSize || level > LogLevel.ERROR)
            {
                flush();
                logPosition = 0;
            }
        }

        public abstract void flush();
    }
}
