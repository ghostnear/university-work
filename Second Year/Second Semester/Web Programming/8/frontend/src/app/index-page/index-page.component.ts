import { Component } from '@angular/core';
import { AuthService } from '../auth.service';
import { Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { NewsListComponent } from '../news-list/news-list.component';

@Component({
  selector: 'app-index-page',
  standalone: true,
  imports: [NewsListComponent],
  templateUrl: './index-page.component.html'
})
export class IndexPageComponent {

  constructor(
    public authService: AuthService,
    private router: Router,
    private httpClient: HttpClient)
  {

  }

  ngOnInit() {
    this.authService.refresh(this.httpClient);
    if(this.authService.getFromLocalStorage("logged_in")== "false") {
      // Redirect to login page
      this.router.navigate(['/login/']);
    }
  }
}