import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { ActivatedRoute } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { AuthService } from '../auth.service';

@Component({
  selector: 'app-view-article-page',
  standalone: true,
  imports: [],
  templateUrl: './view-article-page.component.html'
})
export class ViewArticlePageComponent {
  article: any;

  constructor(
    private route: ActivatedRoute,
    private router: Router,
    private http: HttpClient,
    public authService: AuthService
  ) {
    this.article = {};
  }

  onDelete(): void {
    this.http.delete('https://localhost:7085/News/?id=' + this.article.id).subscribe((response: any) => {
      if(response.status == "success") {
        this.router.navigate(['/']);
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
      }
    });
  }
}
