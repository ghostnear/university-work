import { Routes } from '@angular/router';
import { PageNotFoundComponent } from './page-not-found/page-not-found.component';
import { IndexPageComponent } from './index-page/index-page.component';
import { LoginPageComponent } from './login-page/login-page.component';
import { LogoutPageComponent } from './logout-page/logout-page.component';
import { WriteArticlePageComponent } from './write-article-page/write-article-page.component';

export const routes: Routes = [
    { path: '', component: IndexPageComponent },
    { path: 'login', component: LoginPageComponent },
    { path: 'logout', component: LogoutPageComponent },
    { path: 'article/write', component: WriteArticlePageComponent },
    { path: '**', component: PageNotFoundComponent },  // Wildcard route for a 404 page
];
