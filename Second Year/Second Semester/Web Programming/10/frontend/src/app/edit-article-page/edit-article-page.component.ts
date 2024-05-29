import { Component } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { AuthService } from '../auth.service';
import { FormGroup, FormControl, ReactiveFormsModule } from '@angular/forms';

@Component({
  selector: 'app-edit-article-page',
  standalone: true,
  imports: [ReactiveFormsModule],
  templateUrl: './edit-article-page.component.html'
})
export class EditArticlePageComponent {
  article: any;

  constructor(
    private route: ActivatedRoute,
    private router: Router,
    private http: HttpClient,
    public authService: AuthService
  ) {
    this.article = {};
  }

  editArticleForm = new FormGroup({
    title: new FormControl(''),
    category: new FormControl(''),
    contents: new FormControl(''),
    date: new FormControl('')
  });

  onSubmit() {
    this.http.put(
      'https://localhost:7085/News/?id=' + this.article.id +
      "&title=" + this.editArticleForm.value.title +
      "&category=" + this.editArticleForm.value.category +
      "&contents=" + this.editArticleForm.value.contents +
      "&date=" + this.editArticleForm.value.date +
      "&session_id=" + this.authService.getFromLocalStorage('session_id'), {}).subscribe((response: any) => {
      if(response.status == "success") {
        this.router.navigate(['/view-article/' + this.article.id]);
      }
      else {
        alert(response.message);
      }
    });
  }

  ngOnInit(): void {
    this.article.id = this.route.snapshot.paramMap.get('id');
    this.http.get(`https://localhost:7085/News/?id=${this.article.id}`).subscribe((response: any) => {
      if(response.status != "success") {
        this.router.navigate(['/404/']);
      }
      else {
        this.article = response.data;
        this.editArticleForm.setValue({
          title: this.article.title,
          category: this.article.category,
          contents: this.article.contents,
          date: this.article.date
        });
      }
    });
  }
}
