import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable({providedIn: 'root'})
export class AuthService {
  getFromLocalStorage(key: string) {
    return localStorage.getItem(key);
  }

  refresh(http: HttpClient) {
    var session_id = localStorage.getItem("session_id");
    http.get('http://localhost/8/backend/login-status.php?session_id=' + session_id).forEach((response: any) => {
      if(response.logged_in == false) {
        localStorage.setItem("session_id", '');
        localStorage.setItem("logged_in", 'false');
        localStorage.setItem("user_id", '0');
        localStorage.setItem("username", '');
        localStorage.setItem("elevation", '0');
        localStorage.setItem("session_id", '');
      }
      else {
        localStorage.setItem("logged_in", 'true');
        localStorage.setItem("user_id", response.data.id);
        localStorage.setItem("username", response.data.username);
        localStorage.setItem("elevation", response.data.elevation);
      }
    });
  }
}
