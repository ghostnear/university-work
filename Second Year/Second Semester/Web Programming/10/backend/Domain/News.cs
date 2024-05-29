namespace backend.Domain
{
    public class News
    {
        public int ID { get; set; }
        public string Title { get; set; }
        public string Category { get; set; }
        public DateOnly Date { get; set; }
        public string Contents { get; set; }
        public PublicUser Producer { get; set; }
    }
}
