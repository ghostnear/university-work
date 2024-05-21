import { Component } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { PageHeaderComponent } from './page-header/page-header.component';
import { HttpClientModule } from '@angular/common/http';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet, PageHeaderComponent, HttpClientModule],
  templateUrl: './app.component.html'
})
export class AppComponent {
  title = 'frontend';
}
  