import { Component } from '@angular/core';
import { AuthService } from '../auth.service';
import { Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { FormGroup, FormControl, ReactiveFormsModule } from '@angular/forms';

@Component({
  selector: 'app-write-article-page',
  standalone: true,
  imports: [ReactiveFormsModule],
  templateUrl: './write-article-page.component.html'
})
export class WriteArticlePageComponent {
  constructor(
    public authService: AuthService,
    private router: Router,
    private http: HttpClient
  ) {}

  writeArticleForm = new FormGroup({
    title: new FormControl(''),
    category: new FormControl(''),
    contents: new FormControl('')
  });

  ngOnInit() {
    this.authService.refresh(this.http);
    if(this.authService.getFromLocalStorage("logged_in")== "false" || this.authService.getFromLocalStorage("elevation") == "0") {
      // Redirect to login page
      this.router.navigate(['/login/']);
    }
  }

  onSubmit() {
    this.http.post('https://localhost:7085/News/?title=' + this.writeArticleForm.value.title +
      '&category=' + this.writeArticleForm.value.category + '&contents="' + this.writeArticleForm.value.contents + '"&session_id=' + this.authService.getFromLocalStorage('session_id'), {}).forEach((response: any) => {
      if(response.status == "success") {
        this.router.navigate(['/']);
      }
      else {
        alert(response.message);
      }
    });
  }
}
