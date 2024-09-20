import type { ServerWebSocket } from 'bun';
import { Hono } from 'hono';
import { createBunWebSocket } from 'hono/bun';

import { createWebhookHandler } from './createWebhookHandler';
import { createWebSocketHandler } from './createWebSocketHandler';

export const { upgradeWebSocket, websocket } =
  createBunWebSocket<ServerWebSocket>();

export const createRouter = () => {
  const router = new Hono();

  createWebhookHandler(router);
  createWebSocketHandler(router, upgradeWebSocket);

  return router;
};
