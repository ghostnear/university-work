import { Routes } from '@angular/router';
import { PageNotFoundComponent } from './page-not-found/page-not-found.component';
import { IndexPageComponent } from './index-page/index-page.component';
import { LoginPageComponent } from './login-page/login-page.component';
import { LogoutPageComponent } from './logout-page/logout-page.component';
import { WriteArticlePageComponent } from './write-article-page/write-article-page.component';
import { ViewArticlePageComponent } from './view-article-page/view-article-page.component';
import { EditArticlePageComponent } from './edit-article-page/edit-article-page.component';
import { FilterArticlePageComponent } from './filter-article-page/filter-article-page.component';

export const routes: Routes = [
    { path: '', component: IndexPageComponent },
    { path: 'login', component: LoginPageComponent },
    { path: 'logout', component: LogoutPageComponent },
    { path: 'write-article', component: WriteArticlePageComponent },
    { path: 'view-article/:id', component: ViewArticlePageComponent },
    { path: 'edit-article/:id', component: EditArticlePageComponent },
    { path: 'filter-article', component: FilterArticlePageComponent },
    { path: '**', component: PageNotFoundComponent },  // Wildcard route for a 404 page
];
