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
    this.httpClient.delete('https://localhost:7085/Auth/?session_id=' + localStorage.getItem("session_id")).subscribe(
      () => {
        localStorage.setItem("session_id", '');
        localStorage.setItem("username", '');
        localStorage.setItem("logged_in", 'false');
        localStorage.setItem("user_id", '0');
        localStorage.setItem("elevation", '0');
        localStorage.setItem("session_id", '');
      }
    );
  }
}
