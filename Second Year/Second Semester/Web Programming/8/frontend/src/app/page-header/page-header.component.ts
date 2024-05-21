import { Component } from '@angular/core';
import { AuthService } from '../auth.service';

@Component({
  selector: 'app-page-header',
  standalone: true,
  imports: [],
  templateUrl: './page-header.component.html'
})
export class PageHeaderComponent {
  constructor(public authService: AuthService) {}
}
