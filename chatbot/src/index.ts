import { app } from './app';
import { websocket } from './handlers/router';
import { env } from './lib/env';

export default {
  port: env.PORT,
  fetch: app.fetch,
  websocket,
};
