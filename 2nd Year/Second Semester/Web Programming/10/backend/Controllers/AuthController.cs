using backend.Domain;
using Microsoft.AspNetCore.Mvc;
using MySql.Data.MySqlClient;
using Microsoft.AspNetCore.Cors;

namespace backend.Controllers
{
    [EnableCors("_myAllowSpecificOrigins")]
    [ApiController]
    [Route("[controller]")]
    public class AuthController : ControllerBase
    {
        private static Random random = new Random();

        private static MySqlConnection GetConnection()
        {
            return new MySqlConnection("server=localhost;port=3306;database=WeaselNews;user=root;password=;");
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

        private User? getLoginUser(string username, string password)
        {
            using (MySqlConnection conn = GetConnection())
            {
                conn.Open();
                MySqlCommand cmd = new MySqlCommand("SELECT * FROM Users WHERE Username = '" + username + "' AND Password = '" + password + "'", conn);
                using (MySqlDataReader reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        User result = new User();
                        result.ID = reader.GetInt32("ID");
                        result.Password = reader.GetString("password");
                        result.Username = reader.GetString("username");
                        result.Elevation = reader.GetInt32("elevation");
                        return result;
                    }
                }
            }
            return null;
        }

        [HttpGet(Name = "GetLoginStatus")]
        public LoginStatus GetQuery(string? session_id)
        {
            if(session_id == null)
                return new LoginStatus() {
                    logged_in = false,
                    message = "Session ID not specified",
                    data = null,
                    session_id = session_id
                };

            User current_user = getSessionUser(session_id);
            if(current_user == null)
                return new LoginStatus()
                {
                    logged_in = false,
                    message = "Not logged in.",
                    data = null,
                    session_id = session_id
                };

            return new LoginStatus()
            {
                logged_in = true,
                message = "Logged in.",
                data = new LoginUser()
                {
                    ID = current_user.ID,
                    Username = current_user.Username,
                    Elevation = current_user.Elevation
                },
                session_id = session_id
            };
        }

        private string generateSessionID()
        {
            const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            return new string(Enumerable.Repeat(chars, 40)
                .Select(s => s[random.Next(s.Length)]).ToArray());
        }

        [HttpPost(Name = "LogIn")]
        public LoginStatus Post(string username, string password)
        {
            User future_user = getLoginUser(username, password);

            if(future_user == null)
                return new LoginStatus()
                {
                    logged_in = false,
                    message = "Username or password are wrong.",
                    data = null,
                    session_id = null
                };

            string session_id = generateSessionID();

            using (MySqlConnection conn = GetConnection())
            {
                conn.Open();
                MySqlCommand cmd = new MySqlCommand("INSERT INTO Sessions (session_id, user) VALUES ('" + session_id + "', '" + future_user.ID.ToString() + "')", conn);
                cmd.ExecuteReader();
                conn.Close();
            }

            return new LoginStatus()
            {
                logged_in = true,
                message = "Logged in.",
                data = new LoginUser()
                {
                    ID = future_user.ID,
                    Username = future_user.Username,
                    Elevation = future_user.Elevation
                },
                session_id = session_id
            };
        }

        [HttpDelete(Name = "LogOut")]
        public LoginStatus Delete(string session_id)
        {
            using (MySqlConnection conn = GetConnection())
            {
                conn.Open();
                MySqlCommand cmd = new MySqlCommand("DELETE FROM Sessions WHERE session_id = '" + session_id + "'", conn);
                cmd.ExecuteReader();
                conn.Close();
            }

            return new LoginStatus()
            {
                logged_in = false,
                message = "Logged out.",
                data = null,
                session_id = null
            };
        }
    }
}
