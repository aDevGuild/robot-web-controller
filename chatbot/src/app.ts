import { Hono } from 'hono';
import { createRouter } from './handlers/router';

export const app = new Hono();

app.route('/', createRouter());
