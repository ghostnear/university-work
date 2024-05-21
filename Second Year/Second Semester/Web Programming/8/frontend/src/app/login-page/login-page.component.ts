import { Component } from '@angular/core';
import { AuthService } from '../auth.service';
import { HttpClient } from '@angular/common/http';
import { Router } from '@angular/router';
import { FormControl, FormGroup, ReactiveFormsModule } from '@angular/forms';

@Component({
  selector: 'app-login-page',
  standalone: true,
  imports: [ReactiveFormsModule],
  templateUrl: './login-page.component.html'
})
export class LoginPageComponent {
  errorString: string = '';
  constructor(
    public authService: AuthService,
    private http: HttpClient,
    private router: Router)
  {

  }

  loginForm = new FormGroup({
    username: new FormControl(''),
    password: new FormControl('')
  });

  onLogin() {
    this.http.post('http://localhost/8/backend/login.php', this.loginForm.value).forEach((response: any) => {
      if(response.logged_in == false)
        this.errorString = response.message;
      else {
        this.errorString = '';
        localStorage.setItem("logged_in", 'true');
        localStorage.setItem("user_id", response.data.id);
        localStorage.setItem("username", response.data.username);
        localStorage.setItem("elevation", response.data.elevation);
        localStorage.setItem("session_id", response.session_id);
        this.router.navigate(['/']);
      }
    });
  }
}
