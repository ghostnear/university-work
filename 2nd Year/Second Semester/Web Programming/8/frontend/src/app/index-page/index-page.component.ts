import { Component } from '@angular/core';
import { AuthService } from '../auth.service';
import { NewsListComponent } from '../news-list/news-list.component';
import { ActivatedRoute } from '@angular/router';

@Component({
  selector: 'app-index-page',
  standalone: true,
  imports: [NewsListComponent],
  templateUrl: './index-page.component.html'
})
export class IndexPageComponent {
  filterArgs: any
  constructor(
    public authService: AuthService,
    private route: ActivatedRoute
  )
  {
    this.route.queryParams.subscribe(params => {
      this.filterArgs = params
    })
  }
}
