using backend.Domain;
using Microsoft.AspNetCore.Mvc;
using Microsoft.VisualBasic;
using MySql.Data.MySqlClient;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace backend.Controllers
{
    [ApiController]
    [Route("[controller]")]

    public class NewsController : ControllerBase
    {
        private static MySqlConnection GetConnection()
        {
            return new MySqlConnection("server=localhost;port=3306;database=WeaselNews;user=root;password=;");
        }

        [HttpGet(Name = "GetOneNews")]
        public NewsAnswer GetQuery(int? id)
        {
            if (id == null)
            {
                return new NewsAnswer()
                {
                    status = "error",
                    message = "ID not specified."
                };
            }

            using (MySqlConnection conn = GetConnection())
            {
                conn.Open();
                MySqlCommand cmd = new MySqlCommand("SELECT * FROM News WHERE ID = " + id.ToString(), conn);
                using (MySqlDataReader reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        News item = new News()
                        {
                            ID = reader.GetInt32("ID"),
                            Title = reader.GetString("Title"),
                            Category = reader.GetString("Category"),
                            Date = DateOnly.FromDateTime(reader.GetDateTime("Date")),
                            Contents = reader.GetString("Contents"),
                        };

                        using (MySqlConnection connection = GetConnection())
                        {
                            connection.Open();

                            MySqlCommand cmd2 = new MySqlCommand("SELECT * FROM Users WHERE ID = " + reader.GetInt32("Producer").ToString(), connection);
                            using (MySqlDataReader reader2 = cmd2.ExecuteReader())
                            {
                                while (reader2.Read())
                                {
                                    item.Producer = new PublicUser()
                                    {
                                        ID = reader2.GetInt32("ID"),
                                        Username = reader2.GetString("Username"),
                                    };
                                }
                            }

                            connection.Close();
                        }


                        return new NewsAnswer()
                        {
                            status = "success",
                            message = "Article fetched successfully.",
                            data = item
                        };
                    }
                }
                conn.Close();
            }

            return new NewsAnswer()
            {
                status = "error",
                message = "Article does not exist."
            };
        }

        private User? getSessionUser(string session_id)
        {
            using (MySqlConnection conn = GetConnection())
            {
                conn.Open();
                MySqlCommand cmd = new MySqlCommand("SELECT * FROM Sessions WHERE session_id = '" + session_id + "'", conn);
                using (MySqlDataReader reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        int user_id = reader.GetInt32("user");

                        using (MySqlConnection connection = GetConnection())
                        {
                            connection.Open();

                            MySqlCommand cmd2 = new MySqlCommand("SELECT * FROM Users WHERE ID = " + user_id.ToString(), connection);
                            using (MySqlDataReader reader2 = cmd2.ExecuteReader())
                            {
                                while (reader2.Read())
                                {
                                    User result = new User();
                                    result.ID = reader2.GetInt32("ID");
                                    result.Password = reader2.GetString("password");
                                    result.Username = reader2.GetString("username");
                                    result.Elevation = reader2.GetInt32("elevation");
                                    connection.Close();
                                    conn.Close();
                                    return result;
                                }
                            }
                        }
                    }
                }
            }
            return null;
        }

        [HttpPost(Name = "AddOneNews")]
        public NewsAnswer Post(string title, string category, string contents, string session_id)
        {
            User current_user = getSessionUser(session_id);
            using (MySqlConnection conn = GetConnection())
            {
                conn.Open();
                MySqlCommand cmd = new MySqlCommand(
                    "INSERT INTO News (Title, Category, Contents, Producer) VALUES ('" + title + "', '" + category + "', '" + contents + "', " + current_user.ID.ToString() + ")",
                    conn
                );
                using (MySqlDataReader reader = cmd.ExecuteReader())
                {
                    return new NewsAnswer()
                    {
                        status = "success",
                        message = "Article added successfully.",
                        data = null
                    };
                }
            }
        }

        [HttpDelete(Name = "RemoveOneNews")]
        public NewsAnswer Delete(int id)
        {
            using (MySqlConnection conn = GetConnection())
            {
                conn.Open();
                MySqlCommand cmd = new MySqlCommand(
                    "DELETE FROM News WHERE ID = " + id.ToString(),
                    conn
                );
                using (MySqlDataReader reader = cmd.ExecuteReader())
                {
                    return new NewsAnswer()
                    {
                        status = "success",
                        message = "Article deleted successfully.",
                        data = null
                    };
                }
            }
        }

        [HttpPut(Name = "EditOneNewa")]
        public NewsAnswer Put(int id, string title, string category, string contents)
        {
            using (MySqlConnection conn = GetConnection())
            {
                conn.Open();
                MySqlCommand cmd = new MySqlCommand(
                    "UPDATE News SET Title = '" + title + "', Category = '" + category + "', Contents = '" + contents + "' WHERE ID = " + id,
                    conn
                );
                using (MySqlDataReader reader = cmd.ExecuteReader())
                {
                    return new NewsAnswer()
                    {
                        status = "success",
                        message = "Article edited successfully.",
                        data = null
                    };
                }
            }

            return new NewsAnswer()
            {
                status = "error",
                message = "Error in editing article.",
                data = null
            };
        }
    }
}
