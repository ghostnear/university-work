import { Component, Input } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-news-list',
  standalone: true,
  imports: [],
  templateUrl: './news-list.component.html'
})
export class NewsListComponent {
  news: any;

  @Input() filterArgs: any;

  constructor(private httpClient: HttpClient) {
  }

  ngOnInit() {
    this.httpClient.get('http://localhost/8/backend/all-news.php').subscribe((data: any) => {
      this.news = data;
      if(this.filterArgs)
      {
        if(this.filterArgs.category)
        {
          this.news = this.news.filter((news: any) => news.Category == this.filterArgs.category);
        }

        if(this.filterArgs.startDate)
        {
          this.news = this.news.filter((news: any) => news.Date >= this.filterArgs.startDate);
        }

        if(this.filterArgs.endDate)
        {
          this.news = this.news.filter((news: any) => news.Date <= this.filterArgs.endDate);
        }
      }
    });
  }
}
