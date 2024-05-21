import { Component } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-logout-page',
  standalone: true,
  imports: [],
  templateUrl: './logout-page.component.html'
})
export class LogoutPageComponent {
  constructor(private httpClient: HttpClient) {
    localStorage.setItem("session_id", '');
    localStorage.setItem("username", '');
    localStorage.setItem("logged_in", 'false');
    localStorage.setItem("user_id", '0');
    localStorage.setItem("elevation", '0');
    localStorage.setItem("session_id", '');
    this.httpClient.post('http://localhost/8/backend/logout.php', {});
  }
}
