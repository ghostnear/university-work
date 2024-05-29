import { Component } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { AuthService } from '../auth.service';
import { Router } from '@angular/router';

@Component({
  selector: 'app-page-header',
  standalone: true,
  imports: [],
  templateUrl: './page-header.component.html'
})
export class PageHeaderComponent {
  constructor(
    public authService: AuthService,
    public httpClient: HttpClient,
    public router: Router
  ) {}

  ngOnInit() {
    this.authService.refresh(this.httpClient);
    if(this.authService.getFromLocalStorage("logged_in")== "false") {
      // Redirect to login page
      this.router.navigate(['/login/']);
    }
  }
}
