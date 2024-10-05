import { Component } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Router } from '@angular/router';
import { FormGroup, FormControl, ReactiveFormsModule } from '@angular/forms';

@Component({
  selector: 'app-filter-article-page',
  standalone: true,
  imports: [ReactiveFormsModule],
  templateUrl: './filter-article-page.component.html'
})
export class FilterArticlePageComponent {
  categories = []

  constructor(
    private http: HttpClient,
    private router: Router
  ) { }

  filterForm = new FormGroup({
    category: new FormControl(''),
    startDate: new FormControl(''),
    endDate: new FormControl(''),
  });

  onSubmit() {
    this.router.navigate(['/'], { queryParams: this.filterForm.value });
  }

  ngOnInit() {
    this.http.get('http://localhost/8/backend/get-news-categories.php').subscribe((data: any) => {
      this.categories = data
    })
  }
}
