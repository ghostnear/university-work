import { Component } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-news-list',
  standalone: true,
  imports: [],
  templateUrl: './news-list.component.html'
})
export class NewsListComponent {
  news: any;

  constructor(private httpClient: HttpClient) {
  }

  ngOnInit() {
    this.httpClient.get('http://localhost/8/backend/all-news.php').subscribe((data: any) => {
      this.news = data;
    });
  }
}
