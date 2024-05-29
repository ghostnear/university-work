namespace backend.Domain
{
    public class LoginStatus
    {
        public bool logged_in { get; set; }
        public string message { get; set; }
        public LoginUser data { get; set; }
        public string session_id { get; set; }
    }
}
